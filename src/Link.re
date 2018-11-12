open Utils;
open SharedTypes;

let component = ReasonReact.statelessComponent("Link");
let make = (~href: string, ~className = "", children) => {
  ...component,
  render: _self =>
    <a href className onClick=(ev => {
      ReactEvent.Synthetic.preventDefault(ev);
      ReasonReact.Router.push(href);
    })>
    (children |> ReasonReact.array)
    </a>
};
