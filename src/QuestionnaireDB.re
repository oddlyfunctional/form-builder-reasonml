open SharedTypes;

let decodeQuestion = json =>
  Json.Decode.({
    let description = json |> field("description", string);

    switch (json |> field("type", string)) {
      | "TextField" => TextField(description)
      | "TextArea" => TextArea(description)
      | "AlternateChoices" =>
        AlternateChoices(description, json |> field("choices", list(string)))
      | "MultipleChoices" =>
        MultipleChoices(description, json |> field("choices", list(string)))
      | _ => raise(Not_found)
    }
  });

let optionalList = (l) =>
  switch (l) {
    | None => []
    | Some(l) => l
  };

let decodeQuestionnaire = json =>
  Json.Decode.{
    description: json |> field("description", string),
    questions: json |> optional(field("questions", list(decodeQuestion))) |> optionalList,
  };

let encodeQuestion = question =>
  Json.Encode.(
    switch (question) {
      | TextField(description) =>
        object_([
          ("type", "TextField" |> string),
          ("description", description |> string),
        ])
      | TextArea(description) =>
        object_([
          ("type", "TextArea" |> string),
          ("description", description |> string),
        ])
      | AlternateChoices(description, choices) =>
        object_([
          ("type", "AlternateChoices" |> string),
          ("description", description |> string),
          ("choices", choices |> list(string)),
        ])
      | MultipleChoices(description, choices) =>
        object_([
          ("type", "MultipleChoices" |> string),
          ("description", description |> string),
          ("choices", choices |> list(string)),
        ])
    }
  );

let encodeQuestionnaire = questionnaire =>
  Json.Encode.(
    object_([
      ("description", questionnaire.description |> string),
      ("questions", questionnaire.questions |> list(encodeQuestion)),
    ])
  );

include Firebase.Make({
  type record = questionnaire;
  let path = "/questionnaires";

  let encode = encodeQuestionnaire;
  let decode = decodeQuestionnaire;
});
