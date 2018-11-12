[%raw {| require("dotenv").config() |}]

[@bs.val] external apiKey: string = "process.env.FIREBASE_API_KEY";
[@bs.val] external authDomain: string = "process.env.FIREBASE_AUTH_DOMAIN";
[@bs.val] external databaseURL: string = "process.env.FIREBASE_DATABASE_URL";
[@bs.val] external storageBucket: string = "process.env.FIREBASE_STORAGE_BUCKET";

let firebaseInstance = Firebase.(init({
  apiKey,
  authDomain,
  databaseURL,
  storageBucket,
}));

type context = {
  questionnaireDB: QuestionnaireDB.interface,
  firebaseInstance: Firebase.instance,
  firebase: Firebase.firebase,
};

let defaultValue = {
  questionnaireDB: QuestionnaireDB.make(firebaseInstance),
  firebaseInstance,
  firebase: Firebase.firebase,
};

include Context.Make({
  type t = context;
  let defaultValue = defaultValue;
});
