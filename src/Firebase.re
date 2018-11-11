open Utils;

type firebase;
type db;
[@bs.deriving abstract]
type reference = {
  key: string,
};

type dataSnapshot('a);

type credential = string;
type domain = string;
type url = string;
type path = string;
type error = string;
type id = string;

type config = {
  apiKey: credential,
  authDomain: domain,
  databaseURL: url,
  storageBucket: domain,
};

module type Config {
  type record;
  let path: path;
  let encode: (record) => Js.Json.t;
  let decode: (Js.Json.t) => record;
}

type onComplete = option(error) => unit;

[@bs.module "firebase"] external initializeApp : 'a => firebase = "";
[@bs.send] external database: firebase => db = "";
[@bs.send] external ref_: (db, path) => reference = "ref";
[@bs.send] external set': (reference, Js.Json.t, Js.Nullable.t(error) => unit) => unit = "set";
[@bs.send] external push': (reference, Js.Json.t, Js.Nullable.t(error) => unit) => reference = "push";
[@bs.send] external once: (reference, string, (dataSnapshot(Js.Json.t)) => unit) => reference = "";
[@bs.send] external val_: dataSnapshot(Js.Json.t) => Js.Json.t = "val";
/* TODO: Find a better way to represent the return type for the `val` function
 * and avoid duplicating it */
[@bs.send] external valMany': dataSnapshot(Js.Json.t) => Js.Nullable.t(Js.Dict.t(Js.Json.t)) = "val";

let set = (reference, json, onComplete) =>
  set'(reference, json, Js.Nullable.toOption |- onComplete);

let push = (reference, json, onComplete) =>
  push'(reference, json, Js.Nullable.toOption |- onComplete);

let valMany = snapshot => {
  switch (Js.Nullable.toOption(valMany'(snapshot))) {
    | None => Js.Dict.empty()
    | Some(x) => x
  }
  |> Js.Dict.entries
  |> Array.to_list
};

let encodeConfig = config =>
  Json.Encode.(
    object_([
      ("apiKey", config.apiKey |> string),
      ("authDomain", config.authDomain |> string),
      ("databaseURL", config.databaseURL |> string),
      ("storageBucket", config.storageBucket |> string),
    ])
  );
let init = encodeConfig |- initializeApp;

module Make = (Config: Config) => {
  type interface = {
    create: (~onComplete: onComplete=?, Config.record) => string,
    update: (~onComplete: onComplete=?, string, Config.record) => unit,
    all: (list((id, Config.record)) => unit) => reference,
    get: (string, Config.record => unit) => reference,
  };

  let make = (~transformPath = x => x, instance) => {
    let path = transformPath(Config.path);

    let create = (~onComplete = _ => (), record) =>
      instance
        -> database
        -> ref_(path)
        -> push(Config.encode(record), onComplete)
        -> keyGet;

    let update = (~onComplete = _ => (), id: id, record) =>
      instance
        -> database
        -> ref_(path ++ "/" ++ id)
        -> set(Config.encode(record), onComplete);

    let all = cb =>
      instance
        -> database
        -> ref_(path)
        -> once("value",
             valMany
             |- List.map(((id, record)) => (id, Config.decode(record)))
             |- cb
           );

    let get = (id: id, cb) =>
      instance
        -> database
        -> ref_(path ++ "/" ++ id)
        -> once("value", val_ |- Config.decode |- cb);

    { create, all, get, update };
  };
};
