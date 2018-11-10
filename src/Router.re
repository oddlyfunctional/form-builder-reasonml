open Utils;

type route = NewQuestionnaire | ShowQuestionnaire(string) | NotFound;
type state = route;
type action = route;

let component = ReasonReact.reducerComponent("Router");
let make = (_children) => {
  ...component,
  initialState: () => NewQuestionnaire,
  didMount: ({ send, onUnmount }) => {
    let routeChanged = (url: ReasonReact.Router.url) =>
      switch (url.path) {
        | ["questionnaires", "new"] => send(NewQuestionnaire)
        | ["questionnaires", id] => send(ShowQuestionnaire(id))
        | [] => ReasonReact.Router.push("/questionnaires/new")
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
        | NewQuestionnaire => <NewQuestionnaire />
        | ShowQuestionnaire(id) => <ShowQuestionnaire id />
        | NotFound => <h1>(s("not found"))</h1>
      })

      <Link href="/questionnaires/new">(s("new questionnaire"))</Link>
      (s(" | "))
      <Link href="/questionnaires/1">(s("show 1"))</Link>
    </>
};
