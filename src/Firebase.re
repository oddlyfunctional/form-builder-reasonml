open SharedTypes;
open Utils;

type firebase;
type db;
type reference;
type dataSnapshot('a);

type credential = string;
type domain = string;
type url = string;
type path = string;

type config = {
  apiKey: credential,
  authDomain: domain,
  databaseURL: url,
  storageBucket: domain,
};

module type Config {
  type record;
  let instance: firebase;
  let path: path;
  let encode: (record) => Js.Json.t;
  let decode: (Js.Json.t) => record;
}

[@bs.module "firebase"] external initializeApp : 'a => firebase = "";

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
  [@bs.send] external database: firebase => db = "";
  [@bs.send] external ref_: (db, path) => reference = "ref";
  [@bs.send] external set: (reference, Js.Json.t) => unit = "";
  [@bs.send] external push: (reference) => reference = "";
  [@bs.send] external once: (reference, string, (dataSnapshot(Js.Json.t)) => 'a) => reference = "";
  [@bs.send] external val_: dataSnapshot(Js.Json.t) => Js.Json.t = "val";

  let create = (record) =>
    Config.instance
      -> database
      -> ref_(Config.path)
      -> push
      -> set(Config.encode(record));

  let get = (id, cb) =>
    Config.instance
      -> database
      -> ref_(Config.path ++ "/" ++ id)
      -> once("value", val_ |- Config.decode |- cb);
};
