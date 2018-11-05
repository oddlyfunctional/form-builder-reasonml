open SharedTypes;

let s = ReasonReact.string;
let map = (fn, l) => l |> List.map(fn) |> Array.of_list |> ReasonReact.array;
let mapi = (fn, l) => l |> List.mapi(fn) |> Array.of_list |> ReasonReact.array;
let buildAnswer = (event: ReactEvent.synthetic(ReactEvent.Form.tag)) =>
  Answer(ReactEvent.Form.target(event)##value);
let extractAnswer = fun
  | Answer(value) => value
  | Answers(set) when StringSet.is_empty(set) => ""
  | Answers(set) => StringSet.choose(set);
