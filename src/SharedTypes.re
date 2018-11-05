type description = string;
type choice = string;
type answer = Answer(choice) | Answers(list(choice));

type question =
  | TextField(description)
  | TextArea(description)
  | AlternateChoices(description, list(choice))
  | MultipleChoices(description, list(choice));

type questionnaire = { description, questions: list(question) };
