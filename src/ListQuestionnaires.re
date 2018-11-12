open Utils;
open SharedTypes;

module Component {
  type state = Loading | Loaded(list((Firebase.id, questionnaire)));
  type action = Loaded(list((Firebase.id, questionnaire))) | Create;

  let component = ReasonReact.statelessComponent("ListQuestionnaires");
  let make = (~questionnaires, ~onCreate, _children) => {
    ...component,
    render: _self =>
      <>
        <h1>(s("All questionnaires"))</h1>

        <table className=Styles.table>
          <tbody>
            (questionnaires
             |> map(((id, questionnaire)) => {
                  let path = "/questionnaires/" ++ id;

                  <tr key=id>
                    <td>
                      <Link href=path>(s(questionnaire.description))</Link>
                    </td>

                    <td className=Styles.textRight>
                      <Link href=(path ++ "/edit") className=Styles.primaryButton>(s("Edit"))</Link>
                      <Link href=(path ++ "/answers") className=Styles.secondaryButton>(s("Check answers"))</Link>
                    </td>
                  </tr>
                }))
          </tbody>
        </table>

        <div className=Styles.textCenter>
          <button type_="button" onClick=onCreate className=Styles.primaryButton>
            (s("new questionnaire"))
          </button>
        </div>
      </>
  };
};

module Loader {
  type state = Loading | Loaded(list((Firebase.id, questionnaire)));
  type action = Loaded(list((Firebase.id, questionnaire))) | Create;

  let component = ReasonReact.reducerComponent("ListQuestionnairesLoader");
  let make = (~context: AppContext.context, _children) => {
    ...component,
    initialState: () => Loading,
    didMount: ({ send }) => {
      let userId = Firebase.(firebase->auth->currentUserGet->uidGet);
      context.questionnaireDB.all(~userId, pair => send(Loaded(pair))) |> ignore;
    },
    reducer: (action: action, _state: state) =>
      switch action {
        | Loaded(pair) => ReasonReact.Update(Loaded(pair))
        | Create => ReasonReact.UpdateWithSideEffects(Loading, _ => {
            let questionnaire = {
              description: "",
              questions: [],
              userId: Firebase.(firebase->auth->currentUserGet->uidGet),
            };

            let id: ref(option(string)) = ref(None);
            let onComplete = _ =>
              switch id^ {
                | Some(id) => ReasonReact.Router.push("/questionnaires/" ++ id ++ "/edit")
                | None => raise(Not_found)
              };

            id := Some(context.questionnaireDB.create(questionnaire, ~onComplete));
          })
      },
    render: ({ state, handle }) =>
      switch state {
        | Loading => <h1>(s("Loading..."))</h1>
        | Loaded(questionnaires) => <Component questionnaires onCreate=handle((_, { send }) => send(Create)) />
      }
  };
}

let component = ReasonReact.statelessComponent("ListQuestionnairesWithContext");
let make = _children => {
  ...component,
  render: _ =>
    <AppContext.Consumer>
      ...(context => <Loader context />)
    </AppContext.Consumer>
};
