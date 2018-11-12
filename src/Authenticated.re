open Utils;

module Component {
  type user;
  type auth;

  [@bs.send] external auth: Firebase.firebase => auth = "";
  [@bs.send] external onAuthStateChanged: (auth, Js.Nullable.t(user) => unit) => unit = "";

  type state = Loading | Authenticated(user) | Unauthenticated;
  type action = SetUser(Js.Nullable.t(user));

  let component = ReasonReact.reducerComponent("Authenticated");
  let make = (~context: AppContext.context, children) => {
    ...component,
    initialState: () => Loading,
    didMount: ({ send }) =>
      context.firebase->auth->onAuthStateChanged(user => send(SetUser(user))),
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
