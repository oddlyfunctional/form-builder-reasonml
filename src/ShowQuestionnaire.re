open SharedTypes;
open Utils;

type state = Loading | Loaded(questionnaire) | Submitting | Done | Error(Firebase.error);
type action = Loaded(questionnaire) | Submit(AnswerDB.t) | Done | Error(Firebase.error);

module Component {
  let component = ReasonReact.reducerComponent("ShowQuestionnaire");
  let make = (~context: AppContext.context, ~id, _children) => {
    let answerDB = AnswerDB.make(context.firebase, ~transformPath = path => path ++ "/" ++ id ++ "/answers");

    {
      ...component,
      initialState: () => Loading,
      didMount: ({ send }) =>
        context.questionnaireDB.get(id, q => send(Loaded(q))) |> ignore,
      reducer: (action, _state) =>
        switch action {
          | Loaded(q) => ReasonReact.Update(Loaded(q))
          | Done => ReasonReact.Update(Done)
          | Submit(answer) =>
            ReasonReact.UpdateWithSideEffects(Submitting, ({ send }) => {
              let onComplete = fun
                | Some(error) => send(Error(error))
                | None => send(Done);

              answer |> answerDB.create(~onComplete) |> ignore;
            });
          | Error(error) => ReasonReact.Update(Error(error))
        },
      render: ({ state, handle }) =>
        switch state {
          | Loading => <h1>(s("Loading..."))</h1>
          | Done => <h1>(s("Thank you for filling our survey!"))</h1>
          | Submitting => <h1>(s("Submitting..."))</h1>
          | Error(error) => <h1>(s("Something went wrong: " ++ error))</h1>
          | Loaded(questionnaire) =>
              <Form
                questionnaire
                onSubmit=handle((answers, { send }) => send(Submit(answers)))
              />
        }
    };
  };
};

let component = ReasonReact.statelessComponent("ShowQuestionnaireWithContext");
let make = (~id, _children) => {
  ...component,
  render: _ =>
    <AppContext.Consumer>
      ...(context => <Component id context />)
    </AppContext.Consumer>
};
