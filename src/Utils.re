open SharedTypes;

let s = ReasonReact.string;
let map = (fn, l) => l |> List.map(fn) |> Array.of_list |> ReasonReact.array;
let mapi = (fn, l) => l |> List.mapi(fn) |> Array.of_list |> ReasonReact.array;
