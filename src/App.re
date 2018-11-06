open Utils;
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

type state = {
  questionnaire,
  answers: array(Answer.t),
};

type id = int;
type action = UpdateAnswer(id, Answer.t);

let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
  ...component,
  initialState: () => {
    questionnaire,
    answers: Array.make(List.length(questionnaire.questions), Answer.empty),
  },
  reducer: (action, state) =>
    switch action {
      | UpdateAnswer(index, answer) =>
        ReasonReact.Update({
          ...state,
          answers: state.answers
            |> Array.mapi((i, a) => if (index == i) answer else a)
        })
    },
  render: ({ send, state }) =>
    <>
      <h1>(s(questionnaire.description))</h1>

      (
        questionnaire.questions
        |> mapi((index, question) => {
             let value = state.answers[index];
             let onChange = answer => send(UpdateAnswer(index, answer));

             <div key=string_of_int(index)>
               (switch question {
                 | TextField(description) =>
                   <TextField description value onChange />
                 | TextArea(description) =>
                   <TextArea description value onChange />
                 | AlternateChoices(description, questions) =>
                    <AlternateChoices
                      description
                      questions
                      id=index
                      value
                      onChange
                    />
                 | MultipleChoices(description, questions) =>
                    <MultipleChoices
                      description
                      questions
                      id=index
                      value
                      onChange
                    />
               })
             </div>
        })
      )
    </>,
};
