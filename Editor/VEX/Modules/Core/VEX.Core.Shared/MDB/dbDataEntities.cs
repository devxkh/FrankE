using Microsoft.Data.Entity;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Text;
using VEX.IDAL.MDB;

namespace VEX.Core.Shared.MDB
{
    public partial class dbDataEntities : DbContext
    {
        public dbDataEntities()
     //       : base("name=dbDataEntities")
        {
        }

        //protected override void OnModelCreating(DbModelBuilder modelBuilder)
        //{
        //    throw new UnintentionalCodeFirstException();
        //}
        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<SceneNode>()
                         .HasKey(p => new { p.NodeID, p.SceneID });
        }


        public virtual DbSet<Entity> Entity { get; set; }
        public virtual DbSet<EntityData> EntityData { get; set; }
        public virtual DbSet<SceneNode> SceneNode { get; set; }
        public virtual DbSet<UI> UI { get; set; }
        public virtual DbSet<Scene> Scene { get; set; }
    }
}
