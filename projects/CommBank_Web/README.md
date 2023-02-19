# CommBank Goal Tracker
- [ ] Update The Goal Model: Add an optional icon field of string type.

- [ ] Display The Icon On The Goal Card.

- [ ] Implement An Emoji Picker: 
  - [ ] Install `emoji-mart` at [v3.0.1](https://github.com/missive/emoji-mart/tree/v3.0.1).
  
  - [ ] Create a reusable wrapper that:
    - [ ] Uses `mode` from Redux `themeSlice`.
    - [ ] Takes an `onClick` event handler with params: `(emoji: BaseEmoji, event: React.MouseEvent) => void`.
  
  - [ ] Display the emoji picker based on `useState` hook.
  
  - [ ] Implement the `pickEmojiOnClick` event handler:
    - [ ] Stop event propogation.
    - [ ] Set icon locally.
    - [ ] Close emoji picker.
    - [ ] Create updated goal locally.
    - [ ] Update Redux store.

- [ ] Modify The Goal Manager So Users Can Add And Change Icons: 
  - [ ] Add an `Add icon` component that:
    - [ ] Is only visible when there is no icon.
    - [ ] Uses `TransparentButton` component.
    - [ ] Opens the emoji picker component.

  - [ ] Add an `Icon` component that:
    - [ ] Is only visible when there is an icon.
    - [ ] Uses `TransparentButton` component.
    - [ ] Displays the icon with `font-size: 5.5rem;`.
    - [ ] Opens the emoji picker component.

  - [ ] Add PUT Request To Lib:
    - [ ] Add PUT request to update Goal.
  
  - [ ] Finish Implementing `pickEmojiOnClick` Event Handler:
    - [ ] Import updateGoal PUT request.
    - [ ] Call updateGoal on click.
