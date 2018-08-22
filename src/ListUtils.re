let swap = (items, i, j) => {
  /* find the values that need to be swapped */
  let i_item = List.nth(items, i);
  let j_item = List.nth(items, j);

  /* partial application of mapi to create swapper function */
  let swapper =
    List.mapi((index, item) =>
      switch (index) {
      | x when x == i => j_item
      | x when x == j => i_item
      | _ => item
      }
    );

  /* swap the items in the items list */
  swapper(items);
};

/* Fisher-Yates Shuffle
   https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle */
let shuffle = (items: list('a)) => {
  Random.init(int_of_float(Unix.time()));

  let len = List.length(items);
  let boxed_items = ref(items);

  for (i in len - 1 downto 1) {
    let j = Random.int(i);
    boxed_items := swap(boxed_items^, i, j);
  };

  boxed_items^;
};