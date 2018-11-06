open SharedTypes;
open Utils;

[%raw {| require("dotenv").config() |}]

[@bs.val] external apiKey: string = "process.env.FIREBASE_API_KEY";
[@bs.val] external authDomain: string = "process.env.FIREBASE_AUTH_DOMAIN";
[@bs.val] external databaseURL: string = "process.env.FIREBASE_DATABASE_URL";
[@bs.val] external storageBucket: string = "process.env.FIREBASE_STORAGE_BUCKET";

let instance = Firebase.(init({
  apiKey,
  authDomain,
  databaseURL,
  storageBucket,
}));

let questionnaireDB = QuestionnaireDB.make(instance);

type state = option(questionnaire);
type action = SetQuestionnaire(questionnaire);

let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
  ...component,
  initialState: () => None,
  didMount: ({ send }) =>
    questionnaireDB.get("1", q => q -> SetQuestionnaire -> send) |> ignore,
  reducer: (action, _state) =>
    switch action {
      | SetQuestionnaire(q) => ReasonReact.Update(Some(q))
    },
  render: ({ state }) =>
    switch state {
      | None => <h1>(s("Loading..."))</h1>
      | Some(questionnaire) => <Form questionnaire onSubmit=Js.log />
    }
};
