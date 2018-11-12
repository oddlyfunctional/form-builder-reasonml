open Utils;
open SharedTypes;

let getDescription = fun
  | TextField(description)
  | TextArea(description)
  | AlternateChoices(description, _)
  | MultipleChoices(description, _) => description;

let getChoices = fun
  | TextField(_)
  | TextArea(_) => []
  | AlternateChoices(_, choices)
  | MultipleChoices(_, choices) => choices;

let isTextField = fun
  | TextField(_) => true
  | _ => false;

let isTextArea = fun
  | TextArea(_) => true
  | _ => false;

let isAlternateChoices = fun
  | AlternateChoices(_, _) => true
  | _ => false;

let isMultipleChoices = fun
  | MultipleChoices(_, _) => true
  | _ => false;

let makeTextField = question => TextField(getDescription(question));
let makeTextArea = question => TextArea(getDescription(question));
let makeAlternateChoices = question =>
  AlternateChoices(getDescription(question), getChoices(question));
let makeMultipleChoices = question =>
  MultipleChoices(getDescription(question), getChoices(question));

let component = ReasonReact.statelessComponent("SelectQuestionType");
let make = (~question: question, ~id: string, ~onChange, _children) => {
  let name = "question-type-" ++ id;

  {
    ...component,
    render: _ =>
      <div>
        <label className=Styles.choice>
          <input
            type_="radio"
            name
            checked=isTextField(question)
            onChange=(_ => question |> makeTextField |> onChange)
          />
          (s("Text field"))
        </label>

        <label className=Styles.choice>
          <input
            type_="radio"
            name
            checked=isTextArea(question)
            onChange=(_ => question |> makeTextArea |> onChange)
          />
          (s("Text area"))
        </label>

        <label className=Styles.choice>
          <input
            type_="radio"
            name
            checked=isAlternateChoices(question)
            onChange=(_ => question |> makeAlternateChoices |> onChange)
          />
          (s("Alternate choices"))
        </label>

        <label>
          <input
            type_="radio"
            name
            checked=isMultipleChoices(question)
            onChange=(_ => question |> makeMultipleChoices |> onChange)
          />
          (s("Multiple choices"))
        </label>
      </div>
  };
};
