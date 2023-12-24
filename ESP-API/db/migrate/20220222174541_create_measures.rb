class CreateMeasures < ActiveRecord::Migration[7.0]
  def change
    create_table :measures do |t|
      t.float :measure
      t.string :time
      t.string :measure_type

      t.timestamps
    end
  end
end
