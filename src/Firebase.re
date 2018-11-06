open SharedTypes;
open Utils;

type credential = string;
type domain = string;
type url = string;

type config = {
  apiKey: credential,
  authDomain: domain,
  databaseURL: url,
  storageBucket: domain,
};

type firebase;
type db;
type reference;
type dataSnapshot('a);
type path = string;

[@bs.module "firebase"] external initializeApp : 'a => firebase = "";
[@bs.send] external database: firebase => db = "";
[@bs.send] external ref_: (db, path) => reference = "ref";
[@bs.send] external set: (reference, 'a) => unit = "";
[@bs.send] external push: (reference) => reference = "";
[@bs.send] external once: (reference, string, (dataSnapshot('a)) => unit) => reference = "";
[@bs.send] external val_: dataSnapshot('a) => 'a = "val";

let encodeConfig = config =>
  Json.Encode.(
    object_([
      ("apiKey", config.apiKey |> string),
      ("authDomain", config.authDomain |> string),
      ("databaseURL", config.databaseURL |> string),
      ("storageBucket", config.storageBucket |> string),
    ])
  );

let addPerson = (fb, person) =>
  fb
    -> database
    -> ref_("/users")
    -> push
    -> set(Json.Encode.(
        object_([
          ("name", person.name |> string),
          ("age", person.age |> int),
        ])
    ));

let readPerson = (fb, id, cb) =>
  fb
    -> database
    -> ref_("/users/" ++ id)
    -> once("value", val_ |- cb);
