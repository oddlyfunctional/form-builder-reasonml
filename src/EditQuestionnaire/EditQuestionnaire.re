open Utils;
open SharedTypes;

module Component {
  type index = int;
  type state = questionnaire;
  type action = AddQuestion | UpdateQuestion(index, question) | UpdateDescription(string) | Save;

  let component = ReasonReact.reducerComponent("EditQuestionnaire");
  let make = (~questionnaire, ~db: QuestionnaireDB.interface, ~id, _children) => {
    ...component,
    initialState: () => questionnaire,
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
        | UpdateDescription(description) => ReasonReact.Update({ ...state, description })
        | Save => ReasonReact.SideEffects(_ =>
            db.update(id, state, ~onComplete=(_ => ReasonReact.Router.push("/questionnaires")))
          )
      },
    render: ({ state, handle }) =>
      <form onSubmit=handle((event, { send }) => {
        ReactEvent.Synthetic.preventDefault(event);
        send(Save);
      })>
        <TextInput
          label="Questionnaire's name:"
          value=state.description
          onChange=handle((description, { send }) => send(UpdateDescription(description)))
        />

        (
          state.questions
          |> mapi((index, question) =>
              <QuestionField
                question
                key=string_of_int(index)
                id=string_of_int(index)
                onChange=handle((question, { send }) => send(UpdateQuestion(index, question)))
              />
            )
        )

        <div>
          <button
            type_="button"
            onClick=handle((_, { send }) => send(AddQuestion))
            className=Styles.secondaryButton
          >
            (s("Add question"))
          </button>

          <button
            type_="submit"
            className=Styles.primaryButton
          >
            (s("Save questionnaire"))
          </button>
        </div>
      </form>
  };
};

module Loader {
  type state = Loading | Loaded(questionnaire);
  type action = Loaded(questionnaire);

  let component = ReasonReact.reducerComponent("EditQuestionnaireLoader");
  let make = (~id, ~context: AppContext.context, _children) => {
    ...component,
    initialState: () => Loading,
    didMount: ({ send }) =>
      context.questionnaireDB.get(id, questionnaire => send(Loaded(questionnaire))) |> ignore,
    reducer: (action: action, _state: state) =>
      switch action {
        | Loaded(questionnaire) => ReasonReact.Update(Loaded(questionnaire))
      },
    render: ({ state }) =>
      switch state {
        | Loading => <h1>(s("Loading..."))</h1>
        | Loaded(questionnaire) => <Component questionnaire id db=context.questionnaireDB />
      }
  };
};

let component = ReasonReact.statelessComponent("EditQuestionnaireWithContext");
let make = (~id, _children) => {
  ...component,
  render: _ =>
    <AppContext.Consumer>
      ...(context => <Loader id context />)
    </AppContext.Consumer>
}
