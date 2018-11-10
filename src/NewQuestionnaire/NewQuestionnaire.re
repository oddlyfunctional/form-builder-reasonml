open Utils;
open SharedTypes;

type index = int;
type state = questionnaire;
type action = AddQuestion | UpdateQuestion(index, question);

let component = ReasonReact.reducerComponent("NewQuestionnaire");
let make = (_children) => {
  ...component,
  initialState: () => { description: "", questions: [] },
  reducer: (action: action, state: state) =>
    switch action {
      | AddQuestion => ReasonReact.Update({
          ...state,
          questions: state.questions |> List.append([TextField("")]),
        })
      | UpdateQuestion(index, question) => ReasonReact.Update({
          ...state,
          questions: state.questions |> List.mapi((i, q) => if (i == index) question else q),
        })
    },
  render: ({ state, send }) =>
    <form>
      <h1>(s("Build your form"))</h1>

      (
        state.questions
        |> mapi((index, question) =>
            <QuestionField
              question
              key=string_of_int(index)
              id=string_of_int(index)
              onChange=(question => send(UpdateQuestion(index, question)))
            />
          )
      )

      <button type_="button" onClick=(_ => send(AddQuestion))>(s("Add question"))</button>
    </form>
};
