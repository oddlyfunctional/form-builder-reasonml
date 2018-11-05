open Utils;
open SharedTypes;

let component = ReasonReact.statelessComponent("MultipleChoices");
let make = (~description, ~questions, ~id, ~value, ~onChange, _children) => {
  ...component,
  render: _self => {
    let answers =
      switch value {
        | Answer("") => StringSet.empty
        | Answer(a) => StringSet.singleton(a)
        | Answers(a) => a
      };

    <>
      <h2>(s(description))</h2>
      
      (questions
       |> mapi((index, question) => {
         let checked = StringSet.exists(a => a == question, answers);

         <label key=string_of_int(index)>
          <input
            type_="checkbox"
            value=question
            name=("question" ++ string_of_int(id))
            checked
            onChange=(_event => {
              onChange(Answers(
                if (checked) {
                  StringSet.remove(question, answers)
                } else {
                  StringSet.add(question, answers)
                }
              ));
            })
          />
          (s(question))
         </label>
       })
      )
    </>
  },
};
