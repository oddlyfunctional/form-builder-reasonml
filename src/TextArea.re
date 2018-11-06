open Utils;
open SharedTypes;

let component = ReasonReact.statelessComponent("TextArea");
let make = (~description, ~value, ~onChange, _children) => {
  ...component,
  render: _self =>
    <>
      <h2>(s(description))</h2>
      <textarea
        value=(Answer.get(value))
        onChange=(Answer.fromInput |- onChange)
      ></textarea>
    </>,
};
