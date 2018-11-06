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

module QuestionnaireDB = Firebase.Make({
  type record = questionnaire;
  let instance = instance;

  let path = "/questionnaires";

  let decodeQuestion = json =>
    Json.Decode.({
      let description = json |> field("description", string);

      switch (json |> field("type", string)) {
        | "TextField" => TextField(description)
        | "TextArea" => TextArea(description)
        | "AlternateChoices" => AlternateChoices(description, json |> field("choices", list(string)))
        | "MultipleChoices" => MultipleChoices(description, json |> field("choices", list(string)))
        | _ => raise(Not_found)
      }
    });

  let decodeQuestionnaire = json =>
    Json.Decode.{
      description: json |> field("description", string),
      questions: json |> field("questions", list(decodeQuestion))
    };

  let encodeQuestion = question =>
    Json.Encode.(
      switch (question) {
        | TextField(description) | TextArea(description) =>
          object_([("description", description |> string)])
        | AlternateChoices(description, choices) | MultipleChoices(description, choices) =>
          object_([
            ("description", description |> string),
            ("choices", choices |> list(string)),
          ])
      }
    );

  let encodeQuestionnaire = questionnaire =>
    Json.Encode.(
      object_([
        ("description", questionnaire.description |> string),
        ("questions", questionnaire.questions |> list(encodeQuestion)),
      ])
    );

  let encode = encodeQuestionnaire;
  let decode = decodeQuestionnaire;
});


type state = option(questionnaire);
type action = SetQuestionnaire(questionnaire);

let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
  ...component,
  initialState: () => None,
  didMount: ({ send }) =>
    QuestionnaireDB.get("1", q => q -> SetQuestionnaire -> send) |> ignore,
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
