interface IBase {
    function foo() external view;
}

contract Base is IBase {
    function foo() public virtual view {}
}

interface IExt is IBase {}

contract Ext is IExt, Base {}

contract T { function foo() public virtual view {} }

contract Impl is Ext, T {
    // Used to ask for IBase in the override list.
    function foo() public view override(Base, T) {}
}
