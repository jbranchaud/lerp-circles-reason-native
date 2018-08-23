open Reprocessing;

let colors = [
  ("NAVY", "#001f3f"),
  ("BLUE", "#0074D9"),
  ("AQUA", "#7FDBFF"),
  ("TEAL", "#39CCCC"),
  ("OLIVE", "#3D9970"),
  ("GREEN", "#2ECC40"),
  ("LIME", "#01FF70"),
  ("YELLOW", "#FFDC00"),
  ("ORANGE", "#FF851B"),
  ("RED", "#FF4136"),
  ("MAROON", "#85144b"),
  ("FUCHSIA", "#F012BE"),
  ("PURPLE", "#B10DC9"),
  ("BLACK", "#111111"),
  ("GRAY", "#AAAAAA"),
  ("SILVER", "#DDDDDD"),
];

let width = 450;
let height = 450;

type state = {
  circles: list((int, int)),
  frameCount: int,
  countReset: int,
};

let setup = env => {
  Env.size(~width, ~height, env);
  let circles = [(75, 75), (75, 150), (75, 225), (75, 300), (75, 375)];
  {circles, frameCount: 0, countReset: 2};
};

let lerp = (start: float, finish: float, alpha: float): float =>
  (1.0 -. alpha) *. start +. alpha *. finish;

let draw = (state, env) => {
  Draw.background(Utils.color(~r=255, ~g=255, ~b=255, ~a=255), env);

  List.iteri(
    (index, center_coords) => {
      let (_, hex_color) = List.nth(colors, index + 4);
      let (r, g, b, a) = ColorConverter.hex_to_rgba(hex_color);

      let (xCenter, yCenter) = center_coords;

      Draw.fill(Utils.color(~r, ~g, ~b, ~a), env);
      Draw.ellipse(~center=(xCenter, yCenter), ~radx=25, ~rady=25, env);
    },
    state.circles,
  );

  if (state.frameCount == state.countReset) {
    let new_circles =
      List.mapi(
        (index, coords) => {
          let (xCenter, yCenter) = coords;
          let alpha = float_of_int(index + 1) *. 0.02;
          let new_x_center =
            lerp(xCenter |> float_of_int, 400.0, alpha) |> int_of_float;
          (new_x_center, yCenter);
        },
        state.circles,
      );
    {circles: new_circles, frameCount: 0, countReset: state.countReset};
  } else {
    {...state, frameCount: state.frameCount + 1};
  };
};

run(~setup, ~draw, ());