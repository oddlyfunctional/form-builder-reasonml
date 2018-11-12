open Utils;

let component = ReasonReact.statelessComponent("DescriptionField");
let make = (~label, ~value, ~onChange, _children) => {
  ...component,
  render: _ =>
    <label>
      (s(label))<br />

      <input
        type_="text"
        value
        onChange=(event =>
          onChange(ReactEvent.Form.target(event)##value)
        )
      />
    </label>
};
