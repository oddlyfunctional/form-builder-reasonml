open Utils;

let component = ReasonReact.statelessComponent("AlternateChoices");
let make = (~description, ~questions, ~id, ~value, ~onChange, _children) => {
  ...component,
  render: _self =>
    <>
      <h2>(s(description))</h2>
      
      (questions
       |> mapi((index, question) =>
         <label key=string_of_int(index)>
          <input
            type_="radio"
            name=("question" ++ string_of_int(id))
            value=question
            checked=(Answer.contains(value, question))
            onChange=(Answer.fromInput |- onChange)
          />
          (s(question))
         </label>
       )
      )
    </>,
};
