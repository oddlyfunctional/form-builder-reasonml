open SharedTypes;

let questionnaire: questionnaire = {
  description: "ReasonML Survey",
  questions: [
    TextField("What's your name?"),
    TextArea("Please describe your experience with ReasonML."),
    AlternateChoices("How long have you been studying FP?", [
      "1-3 months",
      "3-12 months",
      "1+ years",
    ]),
    MultipleChoices("Please check the features you like the most in the language:", [
      "Type safety",
      "Type inference",
      "Multi-platform compilation",
      "JS interop",
    ]),
  ],
};

let component = ReasonReact.statelessComponent("App");

let make = (_children) => {
  ...component,
  render: _self => <Form questionnaire />
};
