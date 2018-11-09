open Jest;

describe("Answer", () => {
  open Expect;
  open Answer;

  describe("contains", () => {
    test("it does contain", () =>
      expect("test" |> contains(make("test"))) |> toBe(true)
    );

    test("it doesn't contain", () =>
      expect("something else" |> contains(make("test"))) |> toBe(false)
    );
  });

  describe("get", () => {
    test("it retrieves an item", () =>
      expect(make("test") |> get) |> toBe("test")
    );

    test("it retrieves empty from an empty set", () =>
      expect(empty |> get) |> toBe("")
    );
  });
});
