open SharedTypes;
open Utils;

let component = ReasonReact.statelessComponent("App");
let make = (_children) => {
  ...component,
  render: _self => <Router />
};
