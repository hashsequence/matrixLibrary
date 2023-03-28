/*
https://solaaremupelumi.medium.com/using-es6-import-and-export-statements-for-jest-testing-in-node-js-b20c8bd9041c
*/

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