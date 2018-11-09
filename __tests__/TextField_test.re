open Jest;

describe("Answer", () => {
  open Expect;
  open ReactTestingLibrary;

  let build = (~description="", ~value=Answer.empty, ~onChange=_=>(), ()) =>
    render(<TextField description value onChange />);

  test("renders the description", () => {
    let description = "test description";
    let title = build(~description, ()) |> getByText(~matcher=`Str(description));
    expect(title) |> toMatchSnapshot;
  });

  test("sets the value for the input", () => {
    let answer = "test answer";
    let value = Answer.make(answer);
    let input = build(~value, ()) |> getByValue(answer);
    expect(input) |> toMatchSnapshot;
  });

  Skip.test("calls onChange", () => {
    let result = ref(Answer.empty);
    let onChange = answer => result := answer;

    let answer = "test answer";
    let value = Answer.make(answer);
    let input = build(~onChange, ~value, ()) |> getByValue(answer);

    /* TODO: Find out how to trigger event */
    expect(true) |> toBe(true);
  });
});
