open Utils;
open SharedTypes;

let setDescription = (question, description) =>
  switch question {
    | TextField(_) => TextField(description)
    | TextArea(_) => TextArea(description)
    | AlternateChoices(_, choices) => AlternateChoices(description, choices)
    | MultipleChoices(_, choices) => MultipleChoices(description, choices)
  };

let listSet = (index: int, element: 'a, l: list('a)): list('a) =>
  l |> List.mapi((i, e) => if (i == index) element else e);

let setChoice = (question, index, choice) => {
  let set = listSet(index, choice);

  switch question {
    | AlternateChoices(description, choices) =>
      AlternateChoices(description, choices |> set)
    | MultipleChoices(description, choices) =>
      MultipleChoices(description, choices |> set)
    | _ => raise(Not_found)
  };
}

let appendChoice = (question, choice) =>
  switch question {
    | AlternateChoices(description, choices) =>
      AlternateChoices(description, List.append(choices, [choice]))
    | MultipleChoices(description, choices) =>
      MultipleChoices(description, List.append(choices, [choice]))
    | _ => raise(Not_found)
  };

let component = ReasonReact.statelessComponent("QuestionField");
let make = (~question: question, ~onChange: question => unit, ~id: string, _children) => {
  let setDescription = setDescription(question) |- onChange;
  let setChoice = (index, choice) => setChoice(question, index, choice) |> onChange;
  let appendChoice = appendChoice(question) |- onChange;
  let label = switch question {
    | TextField(_) => "Text field:"
    | TextArea(_) => "Text area:"
    | AlternateChoices(_) => "Alternate choices:"
    | MultipleChoices(_) => "Multiple choices:"
  };

  {
    ...component,
    render: _ =>
      <div>
        (switch question {
          | TextField(description)
          | TextArea(description) =>
            <TextInput
              label
              value=description
              onChange=setDescription
            />
          | AlternateChoices(description, choices)
          | MultipleChoices(description, choices) =>
            <div>
              <TextInput
                label
                value=description
                onChange=setDescription
              />

              (choices |> mapi((index, choice) =>
                <TextInput
                  key=string_of_int(index)
                  label=("Answer " ++ string_of_int(index + 1))
                  value=choice
                  onChange=setChoice(index)
                />
              ))

              <button type_="button" onClick=(_ =>appendChoice(""))>(s("Add choice"))</button>
            </div>
        })

        <SelectQuestionType id question onChange />
      </div>
  };
};
