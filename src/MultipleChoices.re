open Utils;

let component = ReasonReact.statelessComponent("MultipleChoices");
let make = (~description, ~questions, ~id, ~value, ~onChange, _children) => {
  ...component,
  render: _self =>
    <>
      <h2>(s(description))</h2>
      
      (questions
       |> mapi((index, question) => {
         let checked = Answer.contains(value, question);

         <label key=string_of_int(index) className=Styles.choice>
          <input
            type_="checkbox"
            value=question
            name=("question" ++ string_of_int(id))
            checked
            onChange=(_event => {
              onChange(
                if (checked) {
                  Answer.remove(question, value)
                } else {
                  Answer.add(question, value)
                }
              );
            })
          />
          (s(question))
         </label>
       })
      )
    </>,
};
