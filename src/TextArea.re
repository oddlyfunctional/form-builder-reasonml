open Utils;

let component = ReasonReact.statelessComponent("TextArea");
let make = (~description, _children) => {
  ...component,
  render: _self =>
    <>
      <h2>(s(description))</h2>
      <textarea></textarea>
    </>,
};
