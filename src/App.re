open SharedTypes;

let json = [%bs.raw {|
{
  description: "ReasonML Survey",
  questions: [
    {
      type: "TextField",
      description: "What's your name?",
    },
    {
      type: "TextArea",
      description: "Please describe your experience with ReasonML.",
    },
    {
      type: "AlternateChoices",
      description: "How long have you been studying FP?",
      choices: [
        "1-3 months",
        "3-12 months",
        "1+ years",
      ],
    },
    {
      type: "MultipleChoices",
      description: "Please check the features you like the most in the language:",
      choices: [
        "Type safety",
        "Type inference",
        "Multi-platform compilation",
        "JS interop",
      ],
    },
  ],
}
|}];

let parseQuestion = json =>
  Json.Decode.({
    let description = json |> field("description", string);

    switch (json |> field("type", string)) {
      | "TextField" => TextField(description)
      | "TextArea" => TextArea(description)
      | "AlternateChoices" => AlternateChoices(description, json |> field("choices", list(string)))
      | "MultipleChoices" => MultipleChoices(description, json |> field("choices", list(string)))
      | _ => raise(Not_found)
    }
  });

let parseQuestionnaire = json =>
  Json.Decode.{
    description: json |> field("description", string),
    questions: json |> field("questions", list(parseQuestion))
  };

let questionnaire = parseQuestionnaire(json);

let component = ReasonReact.statelessComponent("App");

let make = (_children) => {
  ...component,
  render: _self => <Form questionnaire onSubmit=Js.log />
};
