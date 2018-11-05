open Utils;
open SharedTypes;

let component = ReasonReact.statelessComponent("TextField");
let make = (~description, ~value, ~onChange, _children) => {
  ...component,
  render: _self =>
    <>
      <h2>(s(description))</h2>
      <input
        type_="text"
        value=(extractAnswer(value))
        onChange=(event => event |> buildAnswer |> onChange)
      />
    </>,
};
