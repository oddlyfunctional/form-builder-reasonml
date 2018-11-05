open Utils;
open SharedTypes;

let component = ReasonReact.statelessComponent("TextArea");
let make = (~description, ~value, ~onChange, _children) => {
  ...component,
  render: _self =>
    <>
      <h2>(s(description))</h2>
      <textarea
        value=(extractAnswer(value))
        onChange=(event => event |> buildAnswer |> onChange)
      ></textarea>
    </>,
};
