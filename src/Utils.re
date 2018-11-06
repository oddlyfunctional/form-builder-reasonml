open SharedTypes;

let s = ReasonReact.string;
let (|-) = (g, f, x: 'a) => f(g(x));
let map = fn => List.map(fn) |- Array.of_list |- ReasonReact.array;
let mapi = fn => List.mapi(fn) |- Array.of_list |- ReasonReact.array;
