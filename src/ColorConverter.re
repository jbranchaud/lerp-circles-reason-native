type rgba = (int, int, int, int);

let hex_to_rgba = hex_str: rgba =>
  switch (Str.split(Str.regexp(""), hex_str)) {
  | ["#", r, g, b] => (
      Int32.of_string("0x" ++ r ++ r) |> Int32.to_int,
      Int32.of_string("0x" ++ g ++ g) |> Int32.to_int,
      Int32.of_string("0x" ++ b ++ b) |> Int32.to_int,
      255,
    )
  | ["#", r1, r2, g1, g2, b1, b2] => (
      Int32.of_string("0x" ++ r1 ++ r2) |> Int32.to_int,
      Int32.of_string("0x" ++ g1 ++ g2) |> Int32.to_int,
      Int32.of_string("0x" ++ b1 ++ b2) |> Int32.to_int,
      255,
    )
  | _ =>
    raise(Invalid_argument("Hex value must be of format #RGB or #RRGGBB"))
  };