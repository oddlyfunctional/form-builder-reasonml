open Utils;

let component = ReasonReact.statelessComponent("TextField");
let make = (~description, _children) => {
  ...component,
  render: _self =>
    <>
      <h2>(s(description))</h2>
      <input type_="text" />
    </>,
};
