# Javascript Matrix Library

## Testing

This projects uses the [jest](https://www.npmjs.com/package/jest) package to run tests.

### installation

For this projet I had to make configure babel to use the import/export keywords. Look at the steps below if you are interested in how I did this:

1. install jest 

    npm install --save-dev jest babel-jest @babel/preset-env 

2. create babel.config.js to transpile code to use ES6 import/export keywords

```js
module.exports = {
  presets: [
    [
      '@babel/preset-env',
      {
        targets: {
          node: 'current',
        },
      },
    ],
  ],
};
```
### How to run tests

```bash
npm run test
```

```console
foo@bar:~$ npm run test
```
## Benchmarks

This projects uses the [jest-bench](https://www.npmjs.com/package/jest-bench) package to run benchmarks.

### How to run benchmarks

```bash
npm run bench
```