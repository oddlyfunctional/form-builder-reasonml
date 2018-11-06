type answer = string;

module AnswerSet = Set.Make({
  type t = answer;
  let compare = Pervasives.compare;
});

type t = AnswerSet.t;

let empty = AnswerSet.empty;
let make = AnswerSet.singleton;
let add = AnswerSet.add;
let remove = AnswerSet.remove;
let ofList = AnswerSet.of_list;
let elements = AnswerSet.elements;
let contains = (set, item) => AnswerSet.exists(i => i == item, set);
let get = set => if (AnswerSet.is_empty(set)) "" else AnswerSet.choose(set);

let fromInput = (event: ReactEvent.synthetic(ReactEvent.Form.tag)) =>
  make(ReactEvent.Form.target(event)##value);
