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
let answerDB = AnswerDB.make(instance);

type state = Loading | Loaded(questionnaire) | Submitting | Done | Error(Firebase.error);
type action = Loaded(questionnaire) | Submit(AnswerDB.t) | Done | Error(Firebase.error);

let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
  ...component,
  initialState: () => Loading,
  didMount: ({ send }) =>
    questionnaireDB.get("1", q => send(Loaded(q))) |> ignore,
  reducer: (action, _state) =>
    switch action {
      | Loaded(q) => ReasonReact.Update(Loaded(q))
      | Done => ReasonReact.Update(Done)
      | Submit(answer) =>
        ReasonReact.UpdateWithSideEffects(Submitting, ({ send }) => {
          let onComplete = fun
            | Some(error) => send(Error(error))
            | None => send(Done);

          answer |> answerDB.create(~onComplete);
        });
      | Error(error) => ReasonReact.Update(Error(error))
    },
  render: ({ state, send }) =>
    switch state {
      | Loading => <h1>(s("Loading..."))</h1>
      | Done => <h1>(s("Thank you for filling our survey!"))</h1>
      | Submitting => <h1>(s("Submitting..."))</h1>
      | Error(error) => <h1>(s("Something went wrong: " ++ error))</h1>
      | Loaded(questionnaire) =>
        <Form
          questionnaire
          onSubmit=(answers => send(Submit(answers)))
        />
    }
};
