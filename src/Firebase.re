open Utils;

type firebase;
type db;
type reference;
type dataSnapshot('a);

type credential = string;
type domain = string;
type url = string;
type path = string;
type error = string;

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
[@bs.send] external push: (reference) => reference = "";
[@bs.send] external once: (reference, string, (dataSnapshot(Js.Json.t)) => unit) => reference = "";
[@bs.send] external val_: dataSnapshot(Js.Json.t) => Js.Json.t = "val";

let set = (reference, json, onComplete) =>
  set'(reference, json, Js.Nullable.toOption |- onComplete);

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
    create: (~onComplete: onComplete=?, Config.record) => unit,
    get: (string, Config.record => unit) => reference,
  };

  let make = instance => {
    let create = (~onComplete = _ => (), record) =>
      instance
        -> database
        -> ref_(Config.path)
        -> push
        -> set(Config.encode(record), onComplete);

    let get = (id, cb) =>
      instance
        -> database
        -> ref_(Config.path ++ "/" ++ id)
        -> once("value", val_ |- Config.decode |- cb);

    { create, get };
  };
};
