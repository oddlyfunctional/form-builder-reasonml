let component = ReasonReact.statelessComponent("App");
let make = (_children) => {
  ...component,
  render: _self =>
    <AppContext.Provider>
      <Router />
    </AppContext.Provider>
};
