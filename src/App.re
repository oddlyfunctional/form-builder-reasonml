open Utils;

type description = string;
type choice = string;

type question =
  | TextField(description)
  | TextArea(description)
  | AlternateChoices(description, list(choice))
  | MultipleChoices(description, list(choice));

type questionnaire = { description, questions: list(question) };

let questionnaire: questionnaire = {
  description: "ReasonML Survey",
  questions: [
    TextField("What's your name?"),
    TextArea("Please describe your experience with ReasonML."),
    AlternateChoices("How long have you been studying FP?", [
      "1-3 months",
      "3-12 months",
      "1+ years",
    ]),
    MultipleChoices("Please check the features you like the most in the language:", [
      "Type safety",
      "Type inference",
      "Multi-platform compilation",
      "JS interop",
    ]),
  ],
};

let component = ReasonReact.statelessComponent("App");

let make = (_children) => {
  ...component,
  render: _self =>
    <>
      <h1>(s(questionnaire.description))</h1>

      (
        questionnaire.questions
        |> mapi((index, question) =>
             <div key=string_of_int(index)>
               (switch question {
                 | TextField(description) => <TextField description />
                 | TextArea(description) => <TextArea description />
                 | AlternateChoices(description, questions) =>
                    <AlternateChoices description questions id=index />
                 | MultipleChoices(description, questions) =>
                    <MultipleChoices description questions id=index />
               })
             </div>
           )
      )
    </>,
};
