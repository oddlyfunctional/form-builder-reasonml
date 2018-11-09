let decodeAnswer = json =>
  Json.Decode.({
    json |> array(list(string)) |> Array.map(Answer.ofList)
  });

let encodeAnswer = answer =>
  Json.Encode.(
    answer |> Array.map(Answer.elements) |> array(list(string))
  );

include Firebase.Make({
  type record = array(Answer.t);
  let path = "/questionnaires/1/answers";

  let encode = encodeAnswer;
  let decode = decodeAnswer;
});