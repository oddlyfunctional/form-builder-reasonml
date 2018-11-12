type pair;

[@bs.get] external provider: pair => ReasonReact.reactClass = "Provider";
[@bs.get] external consumer: pair => ReasonReact.reactClass = "Consumer";

[@bs.module "react"] external createContext: 'a => pair = "";

module Make = (Config: {
  type t;
  let defaultValue: t;
}) => {
  let pair = createContext(Config.defaultValue);

  [@bs.deriving abstract]
  type providerProps = { value: Config.t };

  module Provider = {
    let make = (~value: Config.t = Config.defaultValue, children) =>
      ReasonReact.wrapJsForReason(
        ~reactClass=provider(pair),
        ~props=providerProps(~value),
        children,
      );
  };

  module Consumer = {
    let make = (children: (Config.t) => ReasonReact.reactElement) =>
      ReasonReact.wrapJsForReason(
        ~reactClass=consumer(pair),
        ~props=Js.Obj.empty(),
        children
      )
  };
};
