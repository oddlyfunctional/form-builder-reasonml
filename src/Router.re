open Utils;

type id = string;
type route = ListQuestionnaires | EditQuestionnaire(id) | ShowQuestionnaireAnswers(id) | ShowQuestionnaire(id) | NotFound;
type state = route;
type action = route;

let component = ReasonReact.reducerComponent("Router");
let make = (_children) => {
  ...component,
  initialState: () => ListQuestionnaires,
  didMount: ({ send, onUnmount }) => {
    let routeChanged = (url: ReasonReact.Router.url) =>
      switch (url.path) {
        | ["questionnaires"] => send(ListQuestionnaires)
        | ["questionnaires", id, "edit"] => send(EditQuestionnaire(id))
        | ["questionnaires", id, "answers"] => send(ShowQuestionnaireAnswers(id))
        | ["questionnaires", id] => send(ShowQuestionnaire(id))
        | [] => ReasonReact.Router.push("/questionnaires")
        | _ => send(NotFound)
      };
    routeChanged(ReasonReact.Router.dangerouslyGetInitialUrl());

    let watcherID = ReasonReact.Router.watchUrl(routeChanged);
    onUnmount(() => ReasonReact.Router.unwatchUrl(watcherID));
  },
  reducer: (action: action, _state: state) => ReasonReact.Update(action),
  render: ({ state }) =>
    <>
      (switch state {
        | ListQuestionnaires => <ListQuestionnaires />
        | EditQuestionnaire(id) => <EditQuestionnaire id />
        | ShowQuestionnaireAnswers(id) => <ShowQuestionnaireAnswers id />
        | ShowQuestionnaire(id) => <ShowQuestionnaire id />
        | NotFound => <h1>(s("not found"))</h1>
      })

      <Link href="/questionnaires">(s("all questionnaires"))</Link>
    </>
};
