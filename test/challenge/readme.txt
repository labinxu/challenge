  Modules : router, trader, exchange,

  router: responsible for message router between trader and exchange,
  it's an interface for ordermanager.

  trader: enter and cancel orders
  exchange: confirm , trade and cancel orders;

  design:
  the orders can queried by internal and external with different query key,
  In order to ensure the data consistency,similar index view structure is needed.
  there I select vector,(unordered_map or map should better when the data is bigger) to store the orders pointer,
  due to simplify the code ,I using thread instead process.

  ambiguities:
  1.
  I assumed the exchange cancel must after cancelled by trader,becuase it's hardly to loop through
  a unordered_map without the key,vector is also , but bit better after the trader put the cancelled orders put into it.

  2.
  2.1
  I'm not sure when the exchange send the message ExchangeNew, So I made the exchange send it motivately.
  the step for a new order,should be 1. trader enter order get the order identifier
     2). exchange get the identifier and generate a external identifier then send all of them to router.
  2.2
    Not deal with the used up orders specially.

  test:
  1.Actually a test framework I would like to use in my work. google test or cppunit
  2.function test.
  3.module test.

  Additionally,I think it's very good idea to using system emulators in testing.

  run:
  using make tool to build the code.

  make -j4
  there should generate four files:trader, router, exchange, test.

  manually run:
  start trader,router,exchange in different terminal.
  in trader terminal:
  according to the hint
  below example: -> means input
  ./trader
  Input action:[1: enter order], [4:cancel order] ,[6, order status], [8, quantity]
-> 1
  input[internal] market, desk, trader, sequence,price,quantity, like 1,2,3,4,5,6
->  1,2,3,4,5,6
  send:1,1,2,3,4,5,6
  result: successful
  Input action:[1: enter order], [4:cancel order] ,[6, order status], [8, quantity]

  on exchange terminal:
  $ ./exchange
  Input action: [2:Order confirmed], [3: Order traded] ,[5:Order cancelled], [7:Order status]
->  2
  input [internal,external]: market, desk, trader, sequence,eg: 1,2,3,4,external
-> 1,2,3,4,external
  send:2,1,2,3,4,external
  result:successful
  Input action: [2:Order confirmed], [3: Order traded] ,[5:Order cancelled], [7:Order status]


  A totally test run is in test file (but it's just simple)
