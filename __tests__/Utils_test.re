open Jest;

describe("Utils", () => {
  open Expect;
  open Utils;

  test("s", () =>
    expect(s("test")) |> toBe(ReasonReact.string("test"))
  );

  test("|- compose operator", () => {
    let f = (+)(1);
    let g = (*)(2);

    expect(2 |> (f |- g)) |> toBe(6)
  });

  test("map", () =>
    expect(["a"] |> (String.uppercase |- s |> map))
    |> toEqual(ReasonReact.array([| s("A") |]))
  );

  /* TODO: Find out if there's a way to support variadic parameters and apply
   * it to the function below */
  test("mapi", () =>
    expect([1, 2] |> (mapi((a, b) => a + b |> (string_of_int |- s))))
    |> toEqual(ReasonReact.array([| s("1"), s("3") |]))
  );
});
