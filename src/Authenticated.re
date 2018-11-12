open Utils;

module Component {
  [@bs.send] external
  onAuthStateChanged: (Firebase.auth, Js.Nullable.t(Firebase.user) => unit) => unit = "";

  type state = Loading | Authenticated(Firebase.user) | Unauthenticated;
  type action = SetUser(Js.Nullable.t(Firebase.user));

  let component = ReasonReact.reducerComponent("Authenticated");
  let make = (~context: AppContext.context, children) => {
    ...component,
    initialState: () => Loading,
    didMount: ({ send }) =>
      context.firebase->Firebase.auth->onAuthStateChanged(user => send(SetUser(user))),
    reducer: (action: action, _state: state) =>
      switch action {
        | SetUser(user) =>
          switch (Js.Nullable.toOption(user)) {
            | None => ReasonReact.Update(Unauthenticated)
            | Some(user) => ReasonReact.Update(Authenticated(user))
          }
      },
    render: ({ state }) =>
      switch (state) {
        | Loading => <h1>(s("Loading..."))</h1>
        | Unauthenticated => <FirebaseAuth />
        | Authenticated(_) => children |> ReasonReact.array
      }
  };
}

let component = ReasonReact.statelessComponent("Authenticated");
let make = children => {
  ...component,
  render: _self =>
    <AppContext.Consumer>
      ...(context => <Component context>...children</Component>)
    </AppContext.Consumer>
};
