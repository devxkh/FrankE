using System;
using System.Collections.Generic;
using System.Text;
using VEF.Interfaces.Controls;

namespace VEF.Model.Services
{
	/// <summary>
	/// A stack that can be used to support undo/redo functionality. Commmands will be added to the undo
	/// stack initially but moved to the redo stack if they are undone. The user can either add a new command
	/// which will clear the redo stack or they can redo the previously undo operations, moving the commands
	/// back to the undo stack.
	/// </summary>
	public class CommandStack
	{
		/// <summary>
		/// The default size of possible commands to exist in the undo/redo system. The total sum
		/// of both stacks will never exceed this value
		/// </summary>
		private const int DefaultStackSize = 100;


		#region Private Fields

		/// <summary>
		/// A stack of commands that can be undone which will push them onto the redo stack
		/// </summary>
        private Stack<IVEFCommand> mUndoStack;

		/// <summary>
		/// A stack of commands that can be redone which will push them onto the undo stack
		/// </summary>
        private Stack<IVEFCommand> mRedoStack;

		/// <summary>
		/// The maximum number of commands that can exist in the undo/redo system at any given time.
		/// </summary>
		private int mMaxCommands;

		#endregion


		#region Public Events

		/// <summary>
		/// Represents the method that will handle state changes within the command system
		/// </summary>
		/// <param name="canUndo">Whether an undo operation can be performed or not</param>
		/// <param name="canRedo">Whether a redo operation can be performed or not</param>
		public delegate void StateChangedHandler(bool canUndo, bool canRedo);


		/// <summary>
		/// Occurs when the state of the command system changes. State changes occur when
		/// there is a change in whether or not an operation can be undone/redone
		/// </summary>
		public event StateChangedHandler StateChanged;

		#endregion


		#region Public Properties

		/// <summary>
		/// The default maximum capacity of the undo/redo system. There will never be
		/// more than this number of commands in the system if no other capacity is
		/// specified
		/// </summary>
		public static int DefaultMaxCapacity
		{
			get { return DefaultStackSize; }
		}

		/// <summary>
		/// The maximum number of commands that will ever be in this undo/redo system
		/// </summary>
		public int MaxCapacity
		{
			get { return mMaxCommands; }
		}

		/// <summary>
		/// Determine if there are any pending commands that can be redone.
		/// </summary>
		public bool CanRedo
		{
			get { return mRedoStack.Count != 0; }
		}

		/// <summary>
		/// Determine if there are any pending commands that can be undone.
		/// </summary>
		public bool CanUndo
		{
			get { return mUndoStack.Count != 0; }
		}

		#endregion


		#region Construction

		/// <summary>
		/// Constructor. Creates a new CommandStack with the default stack size.
		/// </summary>
		public CommandStack()
		{
            mUndoStack = new Stack<IVEFCommand>();
            mRedoStack = new Stack<IVEFCommand>();

			mMaxCommands = DefaultMaxCapacity;
		}

		#endregion


		#region Command Queries

		/// <summary>
		/// Examine the command that will be performed if an undo operation is executed
		/// </summary>
		/// <returns>The command that will be undone</returns>
        public IVEFCommand PeekUndo()
		{
			return mUndoStack.Peek();
		}

		/// <summary>
		/// Examine the command that will be performed if a redo operation is executed.
		/// </summary>
		/// <returns>The command that will be redone</returns>
        public IVEFCommand PeekRedo()
		{
			return mRedoStack.Peek();
		}

		#endregion


		#region Undo/Redo Support

		/// <summary>
		/// Adds the given command onto the undo/redo stacks. This will clear any redo commands
		/// since the state path has been altered before these commands were originally executed.
		/// This may potentially remove elements from the bottom of the undo stack if adding this
		/// command will exceed the maximum capacity of the system
		/// </summary>
		/// <param name="cmd">The command to add to the system</param>
        public void AddCommand(IVEFCommand cmd)
		{
			mRedoStack.Clear();

			if(mUndoStack.Count == mMaxCommands)
			{
				ReduceStackFromBottom(mUndoStack, 1);
			}

			mUndoStack.Push(cmd);

            //if(cmd.CanExecute(null))
            //{
            //    cmd.Execute(null);
            //}

			// TODO: Handle the case of a non-undoable command being added

			FireStateChanged();
		}


		/// <summary>
		/// Performs the 'Undo' action of the most recently added command to the system.
		/// This command will then be moved to the redo stack so that it can later be redone
		/// if the command supports it.
		/// </summary>
		public void UndoCommand()
		{
			if(mUndoStack.Count == 0)
			{
				throw new InvalidOperationException("There are no commands to be undone");
			}

            IVEFCommand cmd = mUndoStack.Pop();
			cmd.Undo();

			mRedoStack.Push(cmd);

			FireStateChanged();
		}


		/// <summary>
		/// Performs the 'Redo' action of the most recently undone command. This command will
		/// then be moved back to the undo stack so it can later be undone again.
		/// </summary>
		public void RedoCommand()
		{
			if(mRedoStack.Count == 0)
			{
				throw new InvalidOperationException("There are no commands to be redone");
			}

            IVEFCommand cmd = mRedoStack.Pop();
			cmd.Redo();

			mUndoStack.Push(cmd);

			FireStateChanged();
		}

		#endregion


		#region Internal Helpers

		/// <summary>
		/// Removes elements from the bottom of the stack while preserving the original order of
		/// the remaining elements
		/// </summary>
		/// <param name="stack">The stack to remove elements from</param>
		/// <param name="numToRemove">The number of elements to remove from the bottom of the stack</param>
        private void ReduceStackFromBottom(Stack<IVEFCommand> stack, int numToRemove)
		{
			if(stack.Count < numToRemove)
			{
				throw new ArgumentOutOfRangeException("Stack size must be at least equal to the number of elements to remove");
			}

			if(stack.Count == numToRemove)
			{
				stack.Clear();
			}
			else
			{
				// Flip the stack around and then start popping elements off the top of the new stack
				// [which is the bottom of the old stack] and then flip the stack again
                Stack<IVEFCommand> reversedStack = new Stack<IVEFCommand>(stack.Count);

				while(stack.Count > 0)
				{
					reversedStack.Push(stack.Pop());
				}

				for(int i = 0; i < numToRemove; i++)
				{
					reversedStack.Pop();
				}

				while(reversedStack.Count > 0)
				{
					stack.Push(reversedStack.Pop());
				}
			}
		}


		/// <summary>
		/// Cause the StateChanged event to be triggered
		/// </summary>
		private void FireStateChanged()
		{
			if(StateChanged != null)
			{
				StateChanged(CanUndo, CanRedo);
			}
		}

		#endregion


		/// <summary>
		/// Undoes the top most command on the undo stack and removes it from the system. The command
		/// does not transfer to the redo stack.
		/// </summary>
		public void UndoAndPopCommand()
		{
			if (mUndoStack.Count == 0)
			{
				throw new InvalidOperationException("There are no commands to be undone");
			}

            IVEFCommand cmd = mUndoStack.Pop();
			cmd.Undo();

			cmd.Dispose();

			// NOTE: We do not push the command onto the redo stack. It just vanishes

			FireStateChanged();
		}


		/// <summary>
		/// Removes all history from the undo/redo stacks
		/// </summary>
		public void ClearHistory()
		{
            foreach (IVEFCommand cmd in mRedoStack)
			{
				cmd.Dispose();
			}
			mRedoStack.Clear();

			// Do not dispose of the undo stack commands since their actions are still 'in-use' by other
			// editor systems
			mUndoStack.Clear();

			FireStateChanged();
		}


		/// <summary>
		/// Get an iterator over commands on the undo stack
		/// </summary>
		/// <returns>An iterator over commands that are on the undo stack in the reverse order they were initially executed</returns>
        public IEnumerable<IVEFCommand> GetUndoCommandIterator()
		{
            foreach (IVEFCommand cmd in mUndoStack)
			{
				yield return cmd;
			}
		}


		/// <summary>
		/// Get an iterator over commands on the redo stack
		/// </summary>
		/// <returns>An iterator over commands that are on the redo stack in the reverse order they were initially executed</returns>
        public IEnumerable<IVEFCommand> GetRedoCommandIterator()
		{
            IVEFCommand[] redoCmds = mRedoStack.ToArray();
			for (int i = redoCmds.Length - 1; i >= 0; i-- )
			{
				yield return redoCmds[i];
			}
		}
	}
}
