type t = array(Answer.t);

let decodeAnswer = json =>
  Json.Decode.({
    json |> array(list(string)) |> Array.map(Answer.ofList)
  });

let encodeAnswer = answer =>
  Json.Encode.(
    answer |> Array.map(Answer.elements) |> array(list(string))
  );

include Firebase.Make({
  type record = t;
  let path = "/questionnaires";

  let encode = encodeAnswer;
  let decode = decodeAnswer;
});
