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

let decodeQuestionnaire = json =>
  Json.Decode.{
    description: json |> field("description", string),
    questions: json |> field("questions", list(decodeQuestion))
  };

let encodeQuestion = question =>
  Json.Encode.(
    switch (question) {
      | TextField(description) | TextArea(description) =>
        object_([("description", description |> string)])
      | AlternateChoices(description, choices) | MultipleChoices(description, choices) =>
        object_([
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
