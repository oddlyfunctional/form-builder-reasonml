open Utils;
open SharedTypes;

module Component {
  type state = Loading | Loaded(list((Firebase.id, questionnaire)));
  type action = Loaded(list((Firebase.id, questionnaire))) | Create;

  let component = ReasonReact.statelessComponent("ListQuestionnaires");
  let make = (~questionnaires, ~onCreate, _children) => {
    ...component,
    render: _self =>
      <>
        (s("List of questionnaires"))

        <ul>
          (questionnaires
           |> map(((id, questionnaire)) =>
            <li key=id>
              <a href=("/questionnaires/" ++ id)>(s(questionnaire.description))</a>
              (s(" - "))
              <a href=("/questionnaires/" ++ id ++ "/edit")>(s("Edit"))</a>
            </li>
           ))
        </ul>

        <button type_="button" onClick=onCreate>
          (s("new questionnaire"))
        </button>
      </>
  };
};

module Loader {
  type state = Loading | Loaded(list((Firebase.id, questionnaire)));
  type action = Loaded(list((Firebase.id, questionnaire))) | Create;

  let component = ReasonReact.reducerComponent("ListQuestionnairesLoader");
  let make = (~context: AppContext.context, _children) => {
    ...component,
    initialState: () => Loading,
    didMount: ({ send }) => {
      context.questionnaireDB.all(pair => send(Loaded(pair))) |> ignore;
    },
    reducer: (action: action, _state: state) =>
      switch action {
        | Loaded(pair) => ReasonReact.Update(Loaded(pair))
        | Create => ReasonReact.UpdateWithSideEffects(Loading, _ => {
            let questionnaire = { description: "", questions: [] };

            let id: ref(option(string)) = ref(None);
            let onComplete = _ =>
              switch id^ {
                | Some(id) => ReasonReact.Router.push("/questionnaires/" ++ id ++ "/edit")
                | None => raise(Not_found)
              };

            id := Some(context.questionnaireDB.create(questionnaire, ~onComplete));
          })
      },
    render: ({ state, handle }) =>
      switch state {
        | Loading => <h1>(s("Loading..."))</h1>
        | Loaded(questionnaires) => <Component questionnaires onCreate=handle((_, { send }) => send(Create)) />
      }
  };
}

let component = ReasonReact.statelessComponent("ListQuestionnairesWithContext");
let make = _children => {
  ...component,
  render: _ =>
    <AppContext.Consumer>
      ...(context => <Loader context />)
    </AppContext.Consumer>
};
